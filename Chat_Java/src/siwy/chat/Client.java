package siwy.chat;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Toolkit;

public class Client extends JFrame 
{
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	
	private String username ,address;
	private int port;
	
	public Client() 
	{
		setIconImage(Toolkit.getDefaultToolkit().getImage("E:\\!!Projects VS\\!!C++&JAVA\\!MY_PROJECTS\\Chat_Java\\GRAPHICS\\logo_dym.png"));
		setLocationRelativeTo(null);
		setTitle("Chat");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 740, 800);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		setVisible(true);
	}
	
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
		setLocationRelativeTo(null);
		setResizable(false);
		setTitle("Chat");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 740, 800);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		setVisible(true);
	}
}
