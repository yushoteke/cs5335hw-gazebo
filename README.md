
Client-server protocol:

 * Server listens on TCP port.
 * Client connects.
 * Messages are 32-bit length + msgpack msg.
 * Messages can be sent in any order, with any initiator; no responses.
 * Messages are map of string keys including timestamp.

Messages:

General form { topic: String, data: Msg, time: Timestamp }

Either side can subscribe to topics. Messages are only sent to
subscribers.

 * { topic: "subscribe", data: [Topics] }
 * { topic: "unsubscribe", data: [Topics] }

Server -> Client topics (mostly sensors):

 * lidar - [{Angle, Distance}]
 * depth -  
 * compass
 * accelerometer
 * encoder

 
