import java.net.*;
import java.io.*;

public class DayServer {
    public static void main(String[] args) {
        String quote;
        try {
            ServerSocket sock = new ServerSocket(6017);
            while (true) {
                Socket client = sock.accept();
                InputStream input = client.getInputStream();
                BufferedReader buff = new BufferedReader(new InputStreamReader(input));
                quote = buff.readLine();
                PrintWriter pout = new PrintWriter(client.getOutputStream());
                pout.println(quote);
                client.close();
            }
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}