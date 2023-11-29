import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) {
        final int PORT = 12345;

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is listening on port " + PORT);

            while (true) {
                try (Socket socket = serverSocket.accept();
                     InputStream input = socket.getInputStream()) {

                    // Reading the message sent by the client
                    byte[] buffer = new byte[1024];
                    int bytesRead = input.read(buffer);

                    if (bytesRead != -1) {
                        String message = new String(buffer, 0, bytesRead);
                        System.out.println("Received message from client: " + message);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
