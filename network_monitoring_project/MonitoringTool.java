import java.io.IOException;
import java.net.InetAddress;

public class MonitoringTool {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java MonitoringTool <target_ip>");
        } else {
            String targetIp = args[0];
            checkAccessibility(targetIp);
        }
    }

    private static void checkAccessibility(String targetIp) {
        try {
            InetAddress inetAddress = InetAddress.getByName(targetIp);
            if (inetAddress.isReachable(2000)) {
                System.out.println(targetIp + " is reachable!");
            } else {
                System.out.println(targetIp + " is not reachable!");
            }
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
