package siwy.chat;

//IMPORTS BELOW
import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.JTextField;
import java.awt.SystemColor;
import javax.swing.JButton;

public class Login extends JFrame 
{
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtUsername;
	private JLabel lblIpAddress;
	private JTextField textIPAddress;
	private JLabel lblPort;
	private JTextField textPort;
	private JLabel lblNewLabel_1;
	private JLabel lbleg;
	
	//MAIN
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				try 
				{
					Login frame = new Login();
					frame.setVisible(true);
				} 
				catch (Exception e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	public Login() 
	{
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
		
		
		
		
		setFont(new Font("Dialog", Font.PLAIN, 13));
		setTitle("Siwy Chat");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 300, 450);
		setSize(340,450);
		setLocationRelativeTo(null);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.inactiveCaption);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null); //means it is a absolute layout, position of anything, anywhere you want
		
		txtUsername = new JTextField();
		txtUsername.setHorizontalAlignment(SwingConstants.CENTER);
		txtUsername.setFont(new Font("Tahoma", Font.PLAIN, 20));
		txtUsername.setBounds(30, 73, 274, 36);
		contentPane.add(txtUsername);
		txtUsername.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("Username:");
		lblNewLabel.setFont(new Font("Tahoma", Font.PLAIN, 28));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setBounds(30, 37, 274, 36);
		contentPane.add(lblNewLabel);
		
		lblIpAddress = new JLabel("IP Address:");
		lblIpAddress.setHorizontalAlignment(SwingConstants.CENTER);
		lblIpAddress.setFont(new Font("Tahoma", Font.PLAIN, 28));
		lblIpAddress.setBounds(30, 120, 274, 36);
		contentPane.add(lblIpAddress);
		
		textIPAddress = new JTextField();
		textIPAddress.setHorizontalAlignment(SwingConstants.CENTER);
		textIPAddress.setFont(new Font("Tahoma", Font.PLAIN, 20));
		textIPAddress.setColumns(10);
		textIPAddress.setBounds(30, 156, 274, 36);
		contentPane.add(textIPAddress);
		
		lblPort = new JLabel("Port:");
		lblPort.setHorizontalAlignment(SwingConstants.CENTER);
		lblPort.setFont(new Font("Tahoma", Font.PLAIN, 28));
		lblPort.setBounds(30, 227, 274, 36);
		contentPane.add(lblPort);
		
		textPort = new JTextField();
		textPort.setHorizontalAlignment(SwingConstants.CENTER);
		textPort.setFont(new Font("Tahoma", Font.PLAIN, 20));
		textPort.setColumns(10);
		textPort.setBounds(30, 265, 274, 36);
		contentPane.add(textPort);
		
		lblNewLabel_1 = new JLabel("(eg. 192.168.1.4)");
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_1.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblNewLabel_1.setBounds(30, 191, 274, 27);
		contentPane.add(lblNewLabel_1);
		
		lbleg = new JLabel("(eg. 3360)");
		lbleg.setHorizontalAlignment(SwingConstants.CENTER);
		lbleg.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lbleg.setBounds(30, 304, 274, 27);
		contentPane.add(lbleg);
		
		JButton btnNewButton = new JButton("Login");
		btnNewButton.setFont(new Font("Tahoma", Font.PLAIN, 16));
		btnNewButton.setBounds(110, 358, 113, 36);
		contentPane.add(btnNewButton);
	}
}
