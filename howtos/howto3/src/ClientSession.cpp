
#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printString(msg.field_f1());
    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printDataField(msg.field_f1());
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printIntField(msg.field_f1());
    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    std::cerr << "ERROR: Received unexpected message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
}

bool ClientSession::startImpl()
{
    doNextStage();
    return true;
}

std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)

    std::size_t consumed = 0;
    while (true) {
        MsgBuf msgBuf;
        auto consumedTmp = preProcessInput(buf + consumed, bufLen - consumed, msgBuf);

        if (consumedTmp == 0) {
            // Empty buffer or incomplete message remaining
            break;
        }

        consumed += consumedTmp;

        if (!msgBuf.empty()) {
            comms::processAllWithDispatch(&msgBuf[0], msgBuf.size(), m_frame, *this);
        }
    }

    return consumed;
}

void ClientSession::writeMessage(const Message& msg, MsgBuf& output)
{
    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    // The frame will use polymorphic message ID retrieval to
    // prefix message payload with message ID
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(msg, updateIter, output.size());
    }

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }    

    // Introduce special characters
    postProcessOutput(output);
}

void ClientSession::doNextStage()
{
    do {
        if (CommsStage_NumOfValues <= m_currentStage) {
            // Happens in first cycle
            m_currentStage = static_cast<decltype(m_currentStage)>(0);
            break;
        }

        m_currentStage =
            static_cast<decltype(m_currentStage)>(
                static_cast<unsigned>(m_currentStage) + 1);

        if (m_currentStage < CommsStage_NumOfValues) {
            break;
        }

        // Client execution is complete
        getIo().stop();
        return;
    } while (false);

    using NextSendFunc = void (ClientSession::*)();
    static const NextSendFunc Map[] = {
        /* CommsStage_Msg1 */ &ClientSession::sendMsg1,
        /* CommsStage_Msg2Msg3 */ &ClientSession::sendMsg2Msg3,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    MsgBuf output;
    Msg1 msg1;
    msg1.field_f1().value() = "hello";
    writeMessage(msg1, output);

    // Send serialized message 
    sendOutput(&output[0], output.size());
}

void ClientSession::sendMsg2Msg3()
{
    static const std::uint8_t Buf[] = {
        0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x10, 0x11, 0x12,
    };

    MsgBuf output;
    Msg2 msg2;
    comms::util::assign(msg2.field_f1().value(), std::begin(Buf), std::end(Buf));
    writeMessage(msg2, output);

    MsgBuf outputTmp;
    Msg3 msg3;
    msg3.field_f1().value() = 0xabcd;
    writeMessage(msg3, outputTmp);

    // Concatenate buffers
    output.insert(output.end(), outputTmp.begin(), outputTmp.end());

    // Send serialized message 
    sendOutput(&output[0], output.size());
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
