package siwy.chat;

import java.awt.EventQueue;
import java.awt.Font;
import java.awt.Image;
import java.awt.SystemColor;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.EmptyBorder;



public class Login extends JFrame 
{
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtUsername;
	private JLabel lblIpAddress;
	private JTextField txtIPAddress;
	private JLabel lblPort;
	private JTextField txtPort;
	private JLabel lblNewLabel_1;
	private JLabel lbleg;
	private JLabel lblImage;
	
	//private LoginButton login_handler = new LoginButton();
	
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
		
		
		
		
		setFont(new Font("Dialog", Font.PLAIN, 13));
		setTitle("Chat!");
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
		
		txtIPAddress = new JTextField();
		txtIPAddress.setHorizontalAlignment(SwingConstants.CENTER);
		txtIPAddress.setFont(new Font("Tahoma", Font.PLAIN, 20));
		txtIPAddress.setColumns(10);
		txtIPAddress.setBounds(30, 156, 274, 36);
		contentPane.add(txtIPAddress);
		
		lblPort = new JLabel("Port:");
		lblPort.setHorizontalAlignment(SwingConstants.CENTER);
		lblPort.setFont(new Font("Tahoma", Font.PLAIN, 28));
		lblPort.setBounds(30, 227, 274, 36);
		contentPane.add(lblPort);
		
		txtPort = new JTextField();
		txtPort.setHorizontalAlignment(SwingConstants.CENTER);
		txtPort.setFont(new Font("Tahoma", Font.PLAIN, 20));
		txtPort.setColumns(10);
		txtPort.setBounds(30, 265, 274, 36);
		contentPane.add(txtPort);
		
		lblNewLabel_1 = new JLabel("(eg. 192.168.1.4)");
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_1.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblNewLabel_1.setBounds(30, 191, 274, 27);
		contentPane.add(lblNewLabel_1);
		
		lbleg = new JLabel("(eg. 8192)");
		lbleg.setHorizontalAlignment(SwingConstants.CENTER);
		lbleg.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lbleg.setBounds(30, 304, 274, 27);
		contentPane.add(lbleg);
		
		JButton btnNewButton = new JButton("Login");
		//btnNewButton.addActionListener(login_handler);
		btnNewButton.addActionListener(new ActionListener() 
		{
			@Override
			public void actionPerformed(ActionEvent e) 
			{
				//System.out.println("dsadsd");
				String username = txtUsername.getText();
				String ip_address = txtIPAddress.getText();
				int port = Integer.parseInt(txtPort.getText());
				login(username, ip_address, port);
				
			}

		});
		btnNewButton.setFont(new Font("Tahoma", Font.PLAIN, 16));
		btnNewButton.setBounds(110, 358, 113, 36);
		contentPane.add(btnNewButton);
		
		lblImage = new JLabel("");
		Image img = new ImageIcon(this.getClass().getResource("/background.png")).getImage();
		Image newImage = img.getScaledInstance(334, 421, Image.SCALE_DEFAULT);
		lblImage.setIcon(new ImageIcon(newImage));
		lblImage.setBounds(0, 0, 334, 421);
		contentPane.add(lblImage);

//		addWindowListener(new WindowAdapter() 
//		{
//			public void windowClosed(WindowEvent e) 
//			{
//				System.out.println("CLOSED!");
//			}
//		});
	}
	
	/*
	 * Login stuff
	 */
	
	private void login(String name, String address, int port) 
	{
		// TODO Auto-generated method stub
		dispose();	//turning off the window
		new ClientWindow(name, address, port);
		//System.out.println(name + " " + address + " " + port);
	}
}