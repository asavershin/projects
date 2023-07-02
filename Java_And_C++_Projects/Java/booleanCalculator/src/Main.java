import workspace.BooleanExpression;
import workspace.formulanodes.*;
import workspace.myavltree.*;
import workspace.*;

import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        try {
            while (true) {
                Scanner in = new Scanner(System.in);
                System.out.print(">> ");
                String str = in.nextLine();
                if(str.isEmpty()){
                    System.out.println("!!!! Empty input string, try again !!!!");
                    continue;
                }
                if(str.equals("clear")){
                    Global.WorkSpace.clear();
                    continue;
                }
                if(str.equals("end")){
                    return;
                }
                if(str.equals("help")){
                    System.out.println("1) end - is finishing the programme");
                    System.out.println("2) clear - clears variables");
                    System.out.println("3) xk := num -- replaces the value of a variable with a number k with a numher num");
                    continue;
                }
                Pattern pattern = Pattern.compile("^x(\\d+)\\s*:=\\s*(\\d+)$");
                Matcher matcher = pattern.matcher(str);
                if (matcher.matches()) {

                    int firstNumber = Integer.parseInt(matcher.group(1));
                    int secondNumber = Integer.parseInt(matcher.group(2));
                    Global.change(firstNumber, secondNumber);
                    continue;
                }
                BooleanExpression F = new BooleanExpression(str);
                int res = F.calc() ? 1 : 0;
                System.out.println(F.toString() + " = " + res);
            }
        }
        catch(Exception err){
            err.printStackTrace();
            System.out.println(err);
        }
    }
}