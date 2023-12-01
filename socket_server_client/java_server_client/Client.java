import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;

public class Client {
    public static void main(String[] args) {
        // Server IP address and port
        final String SERVER_IP = "localhost";
        final int SERVER_PORT = 12345;

        try (Socket socket = new Socket(SERVER_IP, SERVER_PORT);
             OutputStream output = socket.getOutputStream()) {

            // Sending a message to the server
            String message = "Hello from client!";
            output.write(message.getBytes());
            System.out.println("Message sent to server: " + message);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
