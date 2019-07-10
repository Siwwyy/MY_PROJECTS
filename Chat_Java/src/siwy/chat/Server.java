package siwy.chat;

import java.net.DatagramSocket;
import java.net.SocketException;

public class Server implements Runnable
{
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
	}

	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		running = true;
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
					//Receiving something
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
