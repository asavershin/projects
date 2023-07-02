package workspace;

import workspace.formulanodes.ParamValue;
import workspace.myavltree.AVLTree;

import java.util.Scanner;

public class Global {
    public static AVLTree  WorkSpace = new AVLTree();
    public static void change(int numberOfValue, int newValue){
        Global.WorkSpace.iter = Global.WorkSpace.find(new ParamValue(numberOfValue, false));
        if(!Global.WorkSpace.iter.isEqual(Global.WorkSpace.iter.end())){
            Global.WorkSpace.iter.getData().setVal(newValue != 0);
        }else{
            Global.WorkSpace.insert(new ParamValue(numberOfValue, newValue != 0));
        }
    }
}
