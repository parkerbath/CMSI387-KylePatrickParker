put homework answers here
# Problem 5
---
The bounded buffer class would be appropriate to use for the holding area. The TopicServer's recieve method will not return to its caller until after all of the subscribers have recieved the message. However, with the bounded buffer class acting as an immediate storage, we won't need to wait for all the messages.
