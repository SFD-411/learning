import java.util.*;

// Inspired by Ivan On Tech

public class Main{
    
    ArrayList<Block> blockchain = new ArrayList<>();

    public static void main(String[] args){

        // genesis block
        String[] fundRModule = {"This Is The Initialization of Modular Values", "FUNDR BLOCKCHAIN CREDENTIALS!"};
        Block FundROrigin = new Block( 0, fundRModule );

        System.out.println("Origin Block:");
        for (String stringr : fundRModule) { System.out.println(stringr); }
        System.out.println(FundROrigin.retBlockHash() + "\n");



        // initializes variables for chaining UI loop
        int prevHashHack = FundROrigin.retBlockHash();
        boolean exit = false;
        String module = "This Is The Second Node In The System!";

        do {
            // creates a new block concat input with credentials, and creating
            // hash from previous hash, while assigning new value to previous var
            String[] newModBlock = {module, "FUNDR BLOCKCHAIN CREDENTIALS!"};
            Block ChainBlock = new Block(prevHashHack, newModBlock);
            prevHashHack = ChainBlock.retBlockHash();

            // outputs new chain values to the terminal
            System.out.println("\nNewest FundR Blockchain Hash:");
            for (String stringr : newModBlock) { System.out.println(stringr); }
            System.out.println(prevHashHack + "\n");

            // takes user input as chain values
            Scanner scanLine = new Scanner(System.in);
            System.out.print("\nEnter Your Module: \n(type 'exit' to quit)\n ");
            module = scanLine.nextLine();

        } while (!module.equals("exit"));
    }
}
