import java.awt.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
    private static DataInputStream dataInputStream = null;

    public static void main(String[] args) {
        try(ServerSocket serverSocket = new ServerSocket(5000)){
            System.out.println("> listening to port:5000...");
            Socket clientSocket = serverSocket.accept();
            System.out.println("> " + clientSocket + " connected.");
            dataInputStream = new DataInputStream(clientSocket.getInputStream());
            DataOutputStream dataOutputStream = new DataOutputStream(clientSocket.getOutputStream());
            receiveFile();

            dataInputStream.close();
            dataOutputStream.close();
            clientSocket.close();
        } catch (Exception e){
            e.printStackTrace();
        }
    }

    private static void receiveFile() throws Exception{
        int bytes;
        Scanner scan = new Scanner(System.in);
        System.out.print("> what extension should new file be: ");
        String extension = scan.nextLine();
        FileOutputStream fileOutputStream = new FileOutputStream("receivedFiles/NewReceived." + extension);

        long size = dataInputStream.readLong();
        byte[] buffer = new byte[4*1024];
        while (size > 0 && (bytes = dataInputStream.read(buffer, 0, (int)Math.min(buffer.length, size))) != -1) {
            fileOutputStream.write(buffer,0,bytes);
            size -= bytes;
        }
        fileOutputStream.close();
        System.out.println("> file received!");
        Desktop.getDesktop().open(new File("receivedFiles/NewReceived." + extension));
    }
}