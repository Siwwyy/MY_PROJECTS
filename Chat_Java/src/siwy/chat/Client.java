package siwy.chat;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.border.EmptyBorder;
import javax.swing.text.DefaultCaret;

import java.awt.Toolkit;
import java.awt.GridBagLayout;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import java.awt.GridBagConstraints;
import java.awt.SystemColor;
import java.awt.Color;
import javax.swing.JButton;
import java.awt.Insets;
import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Client extends JFrame 
{
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	
	private String username ,address;
	private int port;
	private JTextField txtMessage;
	private JTextArea history;
	private DefaultCaret caret;
	
	private boolean is_clear_txtrHistory;
	
	/*public Client() 
	{
		setResizable(false);
		setIconImage(Toolkit.getDefaultToolkit().getImage("E:\\!!Projects VS\\!!C++&JAVA\\!MY_PROJECTS\\Chat_Java\\GRAPHICS\\logo_dym.png"));
		setLocationRelativeTo(null);
		setTitle("Chat");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 740, 800);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		
		setVisible(true);
	}*/
	
	public Client(String name, String address, int port) 
	{
		this.username = name;
		this.address = address;
		this.port = port;
		this.is_clear_txtrHistory = false;
		Create_Window();
		Console("Successfully Connected!! \n Username: " + this.username + "\n Ip Adrress: " + this.address + "\n Port: " + this.port);
		Console("Remember about be kind and never insult anyone! \n" + " Great FUN!!");
	}
	
	
	private void Create_Window()
	{
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
		setTitle("Chat! Client null");
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
		caret = (DefaultCaret)history.getCaret();	//for updating the scroll
		JScrollPane scroll = new JScrollPane(history);
		
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
					send(txtMessage.getText());
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
				send(txtMessage.getText());
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
	
	public void Console(String Message)
	{
		//txtrHistory.append(this.username + ": "+Message + "\n\r");
		history.append(Message + "\n\r");
	}
	
	public void send(String message)
	{
		if(message.length() > 0) //or message.equals("") == true | my idea is easier :))
		{
			message = this.username + ": " + message;
			Console(message);
			txtMessage.setText("");
		}
	}
	
	
}
