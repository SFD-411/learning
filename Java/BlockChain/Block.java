import java.util.Arrays;

public class Block{
    
    private int prevBlockHash;
    private int blockHash;
    private String[] modules;

    public Block(int prevBlockHash, String[] modules){
        this.prevBlockHash = prevBlockHash;
        this.modules = modules;

        Object[] blockValue = {Arrays.hashCode(modules), prevBlockHash};
        this.blockHash = Arrays.hashCode(blockValue);
    }

    public int retPrevHash(){
        return prevBlockHash;
    }

    public String[] retModules(){
        return modules;
    }
    
    public int retBlockHash(){
        return blockHash;
    }

}
