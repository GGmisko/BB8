import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import socket

ESP32_IP = "192.168.10.18"   # Cambia por la IP real
ESP32_PORT = 8888

class CmdVelToESP32(Node):

    def __init__(self):
        super().__init__('cmdvel_to_esp32')

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        self.get_logger().info(
            f"Conectando a {ESP32_IP}:{ESP32_PORT}"
        )

        self.sock.connect((ESP32_IP, ESP32_PORT))

        self.subscription = self.create_subscription(
            Twist,
            '/cmd_vel',
            self.cmd_vel_callback,
            10
        )

        self.get_logger().info("Conectado a la ESP32")

    def cmd_vel_callback(self, msg):

        cmd = 'x'

        if msg.linear.x > 0:
            cmd = 'w'

        elif msg.linear.x < 0:
            cmd = 's'

        elif msg.angular.z > 0:
            cmd = 'a'

        elif msg.angular.z < 0:
            cmd = 'd'

        self.sock.send(cmd.encode())


def main(args=None):

    rclpy.init(args=args)

    node = CmdVelToESP32()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()