package siwy.chat;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.EmptyBorder;
import javax.swing.text.DefaultCaret;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ClientWindow extends JFrame implements Runnable
{
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtMessage;
	private JTextArea history;
	private DefaultCaret caret;
	
	private boolean is_clear_txtrHistory;
	private Thread listen_thread, run_thread;
	private boolean running = false;
	
	private Client client;
	
	
	public ClientWindow(String name, String address, int port) 
	{
		this.is_clear_txtrHistory = false;
		client = new Client(name,address,port);
		boolean connect = client.Open_Connection(address);
		Create_Window();
		if(connect == false)
		{
			System.err.println("Connection Failed!! \n");
			Console("Connection Failed!! \n");
		}
		else
		{
			Console("Successfully Connected!! \n Username: " + name + "\n Ip Adrress: " + address + "\n Port: " + port);
			Console("Remember about be kind and never insult anyone! \n" + " Great FUN!!");
			String connection = "/c/" + name;
			client.Send(connection.getBytes());
			run_thread = new Thread(this, "Running Thread");
			running = true;
			run_thread.start();
		}
	}
	
	
	private void Create_Window()
	{
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) 
			{
				System.out.println("CLOSED!");
				String disconnected = "/d/" + client.Get_ID() + "/e/";
				Send(disconnected, false);
				client.close();
				running = false;
			}
		});
		
		setIconImage(Toolkit.getDefaultToolkit().getImage("E:\\!!Projects VS\\!!C++&JAVA\\!MY_PROJECTS\\Chat_Java\\GRAPHICS\\logo_dym.png"));
		//this try catch block is for avoid problems connected with the vary platforms
		try 
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} 
		catch (ClassNotFoundException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		catch (InstantiationException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		catch (IllegalAccessException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		catch (UnsupportedLookAndFeelException e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		setLocationRelativeTo(null);
		setTitle("Chat! Client " + client.Get_Name());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 820, 700);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{600,120};	//SUM = 730
		gbl_contentPane.rowHeights = new int[]{550, 100};	//SUM = 700 	730x700
		gbl_contentPane.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{1.0, 0.0};
		contentPane.setLayout(gbl_contentPane);
		
		history = new JTextArea();
		history.addMouseListener(new MouseAdapter() 
		{
			@Override
			public void mouseClicked(MouseEvent e) 
			{
				//static bool is_pressed = false;
				if(is_clear_txtrHistory == false)
				{ 
					history.setText("");
					is_clear_txtrHistory = true;
				}
				else
				{
					//MAYBE IN FUTURE
				}
			
			}
		});
		history.setEditable(false);
		history.setFont(new Font("Monospaced", Font.PLAIN, 16));
		history.setBackground(new Color(191, 205, 219));
		//caret = (DefaultCaret)history.getCaret();
	
		JScrollPane scroll = new JScrollPane(history);
		caret = (DefaultCaret)history.getCaret();	//for updating the scroll
		//caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
		GridBagConstraints scrollConstraints = new GridBagConstraints();
		scrollConstraints.insets = new Insets(20, 20, 5, 20);
		scrollConstraints.fill = GridBagConstraints.BOTH;
		scrollConstraints.gridx = 0;
		scrollConstraints.gridy = 0;
		scrollConstraints.gridwidth = 0;
		scrollConstraints.insets = new Insets(0,0,0,0);
		contentPane.add(scroll, scrollConstraints);
		
		txtMessage = new JTextField();
		txtMessage.addKeyListener(new KeyAdapter() 
		{
			@Override
			public void keyPressed(KeyEvent e) 
			{
				if(e.getKeyCode() == KeyEvent.VK_ENTER)
				{
//					if(is_clear_txtrHistory == false)
//					{ 
//						txtrHistory.setText("");
//						is_clear_txtrHistory = true;
//					}
					Send(txtMessage.getText(), true);
				}
			}
		});
		txtMessage.setHorizontalAlignment(SwingConstants.LEFT);
		txtMessage.setFont(new Font("Tahoma", Font.PLAIN, 17));
		GridBagConstraints gbc_txtMessage = new GridBagConstraints();
		gbc_txtMessage.insets = new Insets(0, 0, 5, 5);
		gbc_txtMessage.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtMessage.gridx = 0;
		gbc_txtMessage.gridy = 1;
		contentPane.add(txtMessage, gbc_txtMessage);
		txtMessage.setColumns(10);
		
		JButton btnSend = new JButton("Send");
		btnSend.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e) 
			{
				if(is_clear_txtrHistory == false)
				{ 
					history.setText("");
					is_clear_txtrHistory = true;
				}
				Send(txtMessage.getText(), true);
			}
		});
		btnSend.setFont(new Font("Tahoma", Font.BOLD, 16));
		GridBagConstraints gbc_btnSend = new GridBagConstraints();
		gbc_btnSend.insets = new Insets(0, 0, 5, 0);
		gbc_btnSend.fill = GridBagConstraints.HORIZONTAL;
		gbc_btnSend.gridx = 1;
		gbc_btnSend.gridy = 1;
		contentPane.add(btnSend, gbc_btnSend);
		
		//requestFocus();
		//txtMessage.requestFocus();
		txtMessage.requestFocusInWindow();
		setVisible(true);
	}

	
	public void Listen()
	{	
		listen_thread = new Thread("Listen Thread")
		{
			public void run()
			{
				while(running)
				{
					String message = client.Receive();
					if(message.startsWith("/c/"))
					{
						//client.Set_ID(Integer.parseInt(message.substring(3, message.length())));
						
						// message contains -> "/c/8543/e/ and the rest of the message 
						client.Set_ID(Integer.parseInt(message.split("/c/|/e/")[1]));
						Console("Succesfully connected to server!! ID: " + client.Get_ID());
					}
					else if(message.startsWith("/m/"))
					{
//						if(client.Get_ID() == message.)
//						{
//							continue;
//						}
						String text = message.split("/m/|/e/")[1];
						Console(text);
					}
				}
			}
		};
		listen_thread.start();
	}
	
	
	public void Console(String Message)
	{
		//txtrHistory.append(this.username + ": "+Message + "\n\r");
		history.append(Message + "\n\r");
		history.setCaretPosition(history.getDocument().getLength());
	}
	
	
	public void Send(String message, boolean text)
	{
		if(message.length() > 0) //or message.equals("") == true | my idea is easier :))
		{
			if(text == true)
			{
				message = client.Get_Name() + ": " + message;			
				message = "/m/" + message;	//cause m means a message from client
			}
			client.Send(message.getBytes());
			txtMessage.setText("");
		}
	}
	
	
	
	public void run()
	{
		Listen();
	}
	
	

}



