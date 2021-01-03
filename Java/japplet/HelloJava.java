import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JOptionPane;

//
// This applet tutorial came from codejava.net
// 

public class HelloJava extends JApplet{
    private JButton button;
    public void init(){
        button = new JButton("Click Here!");
        button.addActionListener(new ActionListener(){
            public void action(ActionEvent evt){
                JOptionPane.showMessageDialog(HelloJava.this, "Hello Java Applet!!");
            }
        });
        System.out.println("Applet Initialized!");
    }
    public void start(){
        getContentPane().add(button);
        System.out.println("Applet Started!");
    }
    public void stop(){
        System.out.println("Applet Stopped!");
    }
    public void destroy(){
        System.out.println("Applet Destroyed! Tango Neutralized!");
    }
}
