package workspace.formulanodes;
import workspace.Global;
import java.util.Scanner;
public class ParamNode implements FormulaNode{
    int ch;
    public ParamNode(int ch){
        this.ch = ch;
    }
    ParamNode(ParamNode node){
        this.ch = node.ch;
    }
    @Override
    public boolean calc() {
        Global.WorkSpace.iter = Global.WorkSpace.find(new ParamValue(ch, false));
        if(!Global.WorkSpace.iter.isEqual(Global.WorkSpace.iter.end())){
            return Global.WorkSpace.iter.getData().val;
        }else{
            boolean tmp;
            System.out.printf("x%s = ", ch);
            Scanner scanner = new Scanner(System.in);
            int num = scanner.nextInt();
            tmp = num != 0;
            Global.WorkSpace.insert(new ParamValue(ch, tmp));
            return tmp;
        }
    }

    @Override
    public String toString() {
        return String.format("x%s", ch);
    }

    @Override
    public FormulaNode create() {
        return new ParamNode(this);
    }
}
