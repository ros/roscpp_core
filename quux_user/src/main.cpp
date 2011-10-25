#include<quux_msgs/QuuxString.h>

int main()
{
  quux_msgs::QuuxString msg1;
  msg1.string1.data = std::string("Some Text");
  msg1.string2.data = std::string("Some Other Text");

  std::cout << "Im a message: " << std::endl << msg1 << std::endl;

  uint8_t buf[1024];
  ros::serialization::OStream out(buf, sizeof(buf) );
  ros::serialization::serialize(out, msg1);

  std::cout << "Im Serialized" << std::endl;

  quux_msgs::QuuxString msg2;
  ros::serialization::IStream in(buf, sizeof(buf) );
  ros::serialization::deserialize(in, msg2);

  std::cout << "Im a message again: " << std::endl << msg2 << std::endl;
}
