package siwy.chat;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
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

public class Client extends JFrame 
{
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	
	private String username ,address;
	private int port;
	private JTextField txtMessage;
	
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
		Create_Window();
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
		setTitle("Chat Client " + this.username);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 820, 800);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		
		GridBagLayout gbl_contentPane = new GridBagLayout();
		gbl_contentPane.columnWidths = new int[]{600,120};	//SUM = 730
		gbl_contentPane.rowHeights = new int[]{500, 200};	//SUM = 700 	730x700
		gbl_contentPane.columnWeights = new double[]{1.0, Double.MIN_VALUE};
		gbl_contentPane.rowWeights = new double[]{1.0, 0.0};
		contentPane.setLayout(gbl_contentPane);
		
		JTextArea txtrHistory = new JTextArea();
		txtrHistory.setBackground(new Color(191, 205, 219));
		GridBagConstraints gbc_txtrHistory = new GridBagConstraints();
		gbc_txtrHistory.insets = new Insets(20, 20, 5, 20);
		gbc_txtrHistory.fill = GridBagConstraints.BOTH;
		gbc_txtrHistory.gridx = 0;
		gbc_txtrHistory.gridy = 0;
		gbc_txtrHistory.gridwidth = 0;
		gbc_txtrHistory.insets = new Insets(0,0,0,0);
		contentPane.add(txtrHistory, gbc_txtrHistory);
		
		txtMessage = new JTextField();
		txtMessage.setHorizontalAlignment(SwingConstants.CENTER);
		txtMessage.setFont(new Font("Tahoma", Font.PLAIN, 17));
		GridBagConstraints gbc_txtMessage = new GridBagConstraints();
		gbc_txtMessage.insets = new Insets(0, 0, 5, 5);
		gbc_txtMessage.fill = GridBagConstraints.HORIZONTAL;
		gbc_txtMessage.gridx = 0;
		gbc_txtMessage.gridy = 1;
		contentPane.add(txtMessage, gbc_txtMessage);
		txtMessage.setColumns(10);
		
		JButton btnSend = new JButton("Send");
		btnSend.setFont(new Font("Tahoma", Font.BOLD, 16));
		GridBagConstraints gbc_btnSend = new GridBagConstraints();
		gbc_btnSend.insets = new Insets(0, 0, 5, 0);
		gbc_btnSend.fill = GridBagConstraints.HORIZONTAL;
		gbc_btnSend.gridx = 1;
		gbc_btnSend.gridy = 1;
		contentPane.add(btnSend, gbc_btnSend);
		
		
		
		setVisible(true);
	}
}
