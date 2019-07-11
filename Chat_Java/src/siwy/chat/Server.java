package siwy.chat;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.List;

public class Server implements Runnable
{
	private List<ServerClient> Clients_List = new ArrayList<ServerClient>();
	
	private int port;
	private DatagramSocket socket;
	private Thread run_thread, manage_thread, send_thread, receive_thread;
	private boolean running = false;
	
	public Server(int port)
	{
		this.port = port;
		try 
		{
			socket = new DatagramSocket(port);
		} 
		catch (SocketException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		run_thread = new Thread(this, "Server");
		run_thread.start();
	}

	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		running = true;
		System.out.println("Server started on port: " + port);
		Manage_Clients();
		Receive();
	}

	private void Receive() 
	{
		// TODO Auto-generated method stub
		receive_thread = new Thread("Manage")
		{
			public void run()
			{
				while(running)
				{
					byte[] data = new byte[1024];
					//Receiving something
					DatagramPacket packet = new DatagramPacket(data, data.length);
					try 
					{
						socket.receive(packet);
						//packet.getPort();
						//packet.getAddress();
					} 
					catch (IOException e) 
					{
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					String new_string = new String(packet.getData());
					Clients_List.add(new ServerClient("Ja", packet.getAddress(), packet.getPort(), 50));
					System.out.println(Clients_List.get(0).address.toString() + ":" + Clients_List.get(0).port);
					System.out.println(new_string);
				}
			}
		};
		receive_thread.start();
	}

	private void Manage_Clients() 
	{
		// TODO Auto-generated method stub
		manage_thread = new Thread("Manage")
		{
			public void run()
			{
				while(running)
				{
					//Managing something
				}
			}
		};
		manage_thread.start();
	}
}