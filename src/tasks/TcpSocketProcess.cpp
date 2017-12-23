// #ifndef TCP_SOCKET_PROCESS
// #define TCP_SOCKET_PROCESS

// #include <Arduino.h>
// #include <ProcessScheduler.h>
// #include <ESP8266WiFi.h>
// /**
//  * Протокол обмена
//  *
//  * Сообщение От сервера
//  *
//  * Общая информация:
//  *
//  * Описание пакетов клиента:
//  *
//  * CLIENT_INFO - id сообщения 1
//  * Событие происходит при открытии клиенсткого сокета и при запросе информации
//  * клиент отсылает свой идентификатор(номер стойки), ip - Адресс ip-v4,
//  * getChipId, getFreeHeap
//  * Размер пакета 16 байт
//  * | 1 байт - id сообщения | 2 - 5 байты - id aдрес | 6 байт - номер стойки | 7 - 10 байт - id чипа | 11 - 14 байт размер свободной памяти | 15 - 16 байт версия прошивки |
//  *
//  * PRESS_BUTTON - id сообщения 2
//  * Если нажата кнопка на сервер отсылается индекс нажатой кнопки
//  * Размер пакета 2 байта
//  * | 1 байт - id сообщения | 2 байт - данные о номере |
//  * Данные о номере:
//  * | Первые 5 бит - индекс номера | 6-8 бит не используется |
//  *
//  *
//  * Описание пакетов от сервера:
//  *
//  * SET_DIGIT_COMPLETED - id сообщения = 3
//  * Пакет говорящий что какой то номер должен замигать, или наоборот перестать мигать
//  * Размер пакета 2 байта
//  * | 1 байт - id сообщения | 2 байт - данные о номере |
//  * Данные о номере:
//  * | Первые 5 бит - индекс номера | 6-7 бит не используется | 8 бит - мигать или нет |
//  *
//  * UPDATE_ARR_NUMBERS_AND_COMPLETED_STATUS - id сообщения = 4
//  * Пакет передающий всю информацию о номерах которые нужно отображать
//  * Размер пакета 49 байт
//  * | 1 байт - id сообщения | 2 - 49 - данные с о клиентах |
//  * Данные о клиентах 24 блока по 2 байта
//  * Данные о клиенте:
//  * | Первые 14 бит - число - номер клиента | 15 бит не используется | 16 бит - мигать или нет |
//  *
//  * RESTART - id сообщения 5
//  * Пакет говорящий стойке что бы она перезагрузилась
//  * Размер пакета 1 байт
//  * | 1 байт - id сообщения |
//  *
//  * GET INFO - id сообщения 6
//  * Пакет запрашивающий системные данные ( размер свободной памяти и т.п. )
//  * Размер пакета 1 байт
//  * | 1 байт - id сообщения |
//  *
//  **/

// enum CLIENT_EVENTS
// {
//     CLIENT_INFO = 1, // Событие соединения клиента с сервером
//     PRESS_BUTTON = 2 // Событие нажатия кнопки на клиенте
// };

// enum SERVER_EVENTS
// {
//     SET_DIGIT_COMPLETED = 3,                     // требуется утановить какой то номер как completed (что бы мигал)
//     UPDATE_ARR_NUMBERS_AND_COMPLETED_STATUS = 4, // требуется обновить номера клиентов на светодиодных табло и установить как completed (что бы мигали)
//     RESTART = 5,
//     GET_INFO = 6
// };

// struct ClientInfoPackage
// {
//     uint8_t messageId = CLIENT_INFO;
//     uint8_t ip0 = 0;
//     uint8_t ip1 = 0;
//     uint8_t ip2 = 0;
//     uint8_t ip3 = 0;
//     uint8_t deviceId = 0;
//     uint32_t chipId = 0;
//     uint32_t freeHeapSize = 0;
//     uint16_t softwareVersion = 0;
// };

// struct PressButtonPackage
// {
//     uint8_t messageId = PRESS_BUTTON;
//     uint8_t pressButtonIndex = 0;
// };

// struct GetInfoPackage
// {
//     uint8_t messageId = GET_INFO;
// };

// struct RestartPackage
// {
//     uint8_t messageId = RESTART;
// };

// struct UpdateNumbersPackage
// {
//     uint8_t messageId = UPDATE_ARR_NUMBERS_AND_COMPLETED_STATUS;
//     uint8_t numbers[48];
// };

// struct SetDigitCompletedPackage
// {
//     uint8_t messageId = SET_DIGIT_COMPLETED;
//     uint8_t index = 0;
// };

// /**
// * @description Процесс отвечает за принятие, отправку и обработку сообщений полученных
// *              по websocket соединению с nodejs сервером
// *
// */
// class TcpSocketProcess : public Process
// {
//   public:
//     // Call the Process constructor
//     TcpSocketProcess(Scheduler &manager, ProcPriority pr, unsigned int period)
//         : Process(manager, pr, period)
//     {
//     }
//     void send(char *message)
//     {
//     }
//     void message(char *message, CLIENT_EVENTS action)
//     {
//     }
//     void json(char *message, CLIENT_EVENTS action)
//     {
//     }
//     void sendDeviceInfo()
//     {
//         struct ClientInfoPackage info = getDeviceInfo();
//         client.write((uint8_t *)&(info), 16);
//     }
//     void sendButtonPress(uint8_t index)
//     {
//         struct PressButtonPackage info;
//         info.messageId = 2;
//         info.pressButtonIndex = index;
//         client.write((uint8_t *)&(info), 2);
//     }

//   protected:
//     virtual void setup()
//     {
//         client.setNoDelay(true);
//         connect();
//     }

//     // Undo setup()
//     virtual void cleanup()
//     {
//     }

//     // Create our service routine
//     virtual void service()
//     {
//         String data;
//         if (client.connected())
//         {
//             if (client.available())
//             {
//                 const uint8_t BUFF_LENGTH = 128;
//                 uint8_t buff[BUFF_LENGTH];
//                 for (int i = 0; i < BUFF_LENGTH; i++)
//                 {
//                     buff[i] = 0;
//                 }
//                 int i = client.read((uint8_t *)&buff, BUFF_LENGTH);
//                 for (int i = 0; i < BUFF_LENGTH; i++)
//                 {
//                     Serial.printf("%u ", buff[i]);
//                 }
//                 uint8_t cur = 0;
//                 while (cur < BUFF_LENGTH)
//                 {
//                     switch (buff[cur])
//                     {
//                     case SET_DIGIT_COMPLETED:
//                         setCompletedNumber(buff[cur + 1]);
//                         sendButtonPress(buff[cur + 1]);
//                         cur += 2;
//                         break;
//                     case GET_INFO:
//                         sendDeviceInfo();
//                         cur++;
//                         break;
//                     case RESTART:
//                         // ESP.restart();
//                         Serial.println("restart");
//                         cur++;
//                         break;
//                     case UPDATE_ARR_NUMBERS_AND_COMPLETED_STATUS:
//                         updateNumbers((void *)(buff + cur));
//                         cur += 49;
//                         break;
//                     default:
//                         cur++;
//                     }
//                 }
//             }
//         }
//         else
//         {
//             Serial.printf("Client disconnected. wait to reconnect %d", sleep);
//             delay(3000);
//             ESP.restart();
//         }
//     }

//   private:
//     void sendAllMessages()
//     {
//         if (client.connected())
//         {
//         }
//     }
//     void connect()
//     {
//         // Connect to the websocket server
//         if (client.connect("192.168.0.45", 1677))
//         {
//             tcp_connected = true;
//             Serial.println("Connected");
//             sendDeviceInfo();
//         }
//         else
//         {
//             Serial.println("TCP Connection failed.");
//             delay(100);
//             tcp_connected = false;
//         }
//     }
//     void updateNumbers(void *buff)
//     {
//         struct UpdateNumbersPackage *info = 0;
//         info = (struct UpdateNumbersPackage *)buff;
//         Serial.printf("message id %d \n", info->messageId);
//         for (int i = 0; i < 48; i += 2)
//         {
//             bool isCompleted = (info->numbers[i]) >> 7;
//             uint16_t clientNumber = ((info->numbers[i] << 8) & ~(1 << 15)) + (info->numbers[i + 1]);
//             Serial.printf("%u-%u-%u,", i, clientNumber, isCompleted);
//         }
//     }
//     void setCompletedNumber(uint8_t index)
//     {
//         bool isCompleted = index >> 7;
//         uint8_t index = index & ~(1 << 7);
//     }
//     ClientInfoPackage getDeviceInfo()
//     {
//         struct ClientInfoPackage info;
//         info.messageId = 1;
//         info.ip0 = WiFi.localIP()[0];
//         info.ip1 = WiFi.localIP()[1];
//         info.ip2 = WiFi.localIP()[2];
//         info.ip3 = WiFi.localIP()[3];
//         info.freeHeapSize = ESP.getFreeHeap();
//         info.chipId = ESP.getChipId();
//         info.deviceId = 3;
//         info.softwareVersion = 1;
//         return info;
//     }
//     bool tcp_connected = false;
//     uint8_t sleep = 0;
//     WiFiClient client;
// };

// #endif
