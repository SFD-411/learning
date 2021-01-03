import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

// 
// this lesson in Java was influenced by codejava.net
//

public class ScreenShot{
    public static void main(String[] args){
        try{
            Robot robot = new Robot();
            String format = "jpg";
            String fileName = "ScreenShot." + format;

            Rectangle screen = new Rectangle(Toolkit.getDefaultToolkit().getScreenSize());
            BufferedImage screenImage = robot.createScreenCapture(screen);
            ImageIO.write(screenImage, format, new File(fileName));

            System.out.println("Snapped a Screen Shot!");
        } catch (AWTException | IOException ex){
            System.err.println(ex);
        }
    }
}
