package workspace;
import stringiterator.StringIterator;
import workspace.formulanodes.*;
import stringiterator.StringIterator.*;
import java.util.Iterator;
import java.util.ArrayDeque;


public class BooleanExpression {

    static final char[][] actionsTable = {
        //\0  (  )  X/const  &  ~  the rest
        { 0, 2, 5,    1,    2, 2, 2},// \0
        { 3, 2, 3,    1,    3, 2, 3},// &
        { 5, 2, 4,    1,    2, 2, 2},// (
        { 3, 2, 3,    1,    3, 2, 3},// ~
        { 3, 2, 3,    1,    2, 2, 3} // the rest
    };

    static int actionsRowNumber(char ch) {
        switch (ch)
        {
            case   0: return 0;
            case '&': return 1;
            case '(': return 2;
            case '~': return 3;

            ///////////////////
            //case '*': return 3;
            //case '/': return 4;
            //case '^': return 5;
            //case '=': return 8;
        }
        return 4;
    }

    static int actionsColNumber(char ch) {
        switch (ch)
        {
            case 0:   return 0;
            case '(': return 1;
            case ')': return 2;
            case '&': return 4;
            case '~': return 5;
        }
        if (ch == 'v' || ch == '^' || ch == '|' || ch == '>' || ch == '<' || ch == '=' || ch == '+')
        {
            return 6;
        }
        return 3;
    }

    //Превращаем инфиксную запись в постфиксную
    public static String Infix2Postfix_(String instr) throws Exception {
        StringBuilder outstr = new StringBuilder();
        int i = 0, j = 0; // i - index for input str, j - index for output str
        int row, col;
        int xNumber;
        int len = instr.length();
        char action;
        ArrayDeque<Character> S = new ArrayDeque<>();
//        System.out.println(123);
        do{
            col = actionsColNumber((len <= i) ? (char)0 : instr.charAt(i));
            row = S.isEmpty() ? 0 : actionsRowNumber(S.peek());
            action = actionsTable[row][col];
//            System.out.println((S.isEmpty()? 'N' : S.peek()) + "|" + ((len <= i) ? (char)0 : instr.charAt(i)) + "|" + (int)action);
            switch (action) {
                case 1:
                    if (((len <= i) ? (char)0 : instr.charAt(i)) == 'x') {
                        ++i;
                        //xNumber = xIndexGetter(instr, i);
                        outstr.append('x');
                        //xNumberWriter(outstr, xNumber, j);
                        while (Character.isDigit(instr.charAt(i))) {
                            outstr.append(instr.charAt(i));
                            ++i;
                            ++j;
                        }

                        //--j;
                    } else {
                        if (((len <= i) ? (char)0 : instr.charAt(i)) == '0') {
                            outstr.append('q');
                        } else if (((len <= i) ? (char)0 : instr.charAt(i)) == '1') {
                            outstr.append('w');
                        } else {
                            //std::cout << instr[i] << std::endl;
                            String err = outstr +
                                    "          " +
                                    S.toString();
                            throw new Exception(err);
                        }
                        ++j;
                        ++i;
                    }
                    break;
                case 2:
                    S.push(instr.charAt(i));
                    ++i;
                    break;
                case 3:
                    outstr.append(S.pop());
                    ++j;
//                    S.pop();
                    break;
                case 4:
                    S.pop();
                    ++i;
                    break;
                case 5:
                    throw new Exception("Got error");
                case 0:
                    break;
            }
            //std::cout << outstr << std::endl;
//            System.out.println(outstr + "   " + i + "   " + len);
        }while(action != 0);
        return outstr.toString();
    }
    FormulaNode root;

    //Постфиксную запись в обычное дерево
    public static FormulaNode postfixToTree_(String str){
        int index = 0; // Номер элемента во входной строке
        char ch;
        FormulaNode result;
        FormulaNode left;
        FormulaNode right;
        ArrayDeque<FormulaNode> S = new ArrayDeque<>();

        int tmpInt = 1;
        int tmp = 0;
        StringBuilder ind;

        StringIterator iter = new StringIterator(str);
        try
        {
            while (iter.hasNext())
            {
                ch = iter.next();
                left = null;
                right = null;
                switch (ch)
                {
                    case '&':
                        if (S.isEmpty()) throw new Exception("First pop error with &");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with &");
                        left = S.pop();
                        result = new ConjunctionNode(left, right);
                        break;
                    case 'v':
                        if (S.isEmpty()) throw new Exception("First pop error with v");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with v");
                        left = S.pop();
                        result = new DisjunctionNode(left, right);
                        break;
                    case '>':
                        if (S.isEmpty()) throw new Exception("First pop error with >");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with >");
                        left = S.pop();
                        result = new ImplicationNode(left, right);
                        break;
                    case '<':
                        if (S.isEmpty()) throw new Exception("First pop error with <");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with <");
                        left = S.pop();
                        result = new ReImplicationNode(left, right);
                        break;
                    case '+':
                        if (S.isEmpty()) throw new Exception("First pop error with +");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with +");
                        left = S.pop();
                        result = new XORNode(left, right);
                        break;
                    case '|':
                        if (S.isEmpty()) throw new Exception("First pop error with |");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with |");
                        left = S.pop();
                        result = new ShefferStrokeNode(left, right);
                        break;
                    case '^':
                        if (S.isEmpty()) throw new Exception("First pop error with ^");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with ^");
                        left = S.pop();
                        result = new PierceArrowNode(left, right);
                        break;
                    case '=':
                        if (S.isEmpty()) throw new Exception("First pop error with =");
                        right = S.pop();
                        if (S.isEmpty()) throw new Exception("Second pop error with =");
                        left = S.pop();
                        result = new EquivalentNode(left, right);
                        break;
                    case '~':
                        if (S.isEmpty()) throw new Exception("Got error with ~");
                        left = S.pop();
                        result = new NegationNode(left);
                        break;
                    case 'q':
                        result = new NumNode(false);
                        break;
                    case 'w':
                        result = new NumNode(true);
                        break;
                    case 'x':
                        ind = new StringBuilder();
                        while (iter.hasNext() && ('0' <= iter.current()) && (iter.current() <= '9')) {

                            ind.append(Character.getNumericValue(iter.next()));
                        }
                        tmp = Integer.parseInt(ind.toString());
                        result = new ParamNode(tmp);
                        break;
                    default:
                        throw new Exception(String.format("Met unknown symbol: %d", (int)str.length()));
                }

                S.push(result);
            }
            if (S.size() > 1)
            {
                left = right = null;
                throw new Exception("Wrong postfix form");
            }
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        result = S.pop();
        return result;

    }

    //фильтруем входные данные от ненужного мусор типа пробелов
    public static String InfixFilter_(String instr) throws Exception {
        StringBuilder outstr = new StringBuilder();
        int i = 0, j = 0; // i - индекс во входной строке, j - в выходной
        char ch;
        char prev = 0;
        char[] buf = new char[256];
        int bufLen = 0;
        StringIterator iter = new StringIterator(instr);
        while (iter.hasNext()) {
            ch = iter.next();
            // Пропускаем пробел и табуляцию
            if (ch == ' ' || ch == '\t') {
                continue;
            }
            if (ch == 'x') {
                if (bufLen == 1) {
                    outstr.append(buf[0]);
                    bufLen = 0;
                }
                outstr.append(ch);
            }
            else if ((ch >= 'a' && ch < 'v') || (ch > 'v' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
                if (prev == 'x') {
                    outstr.append(ch);
                    continue;
                }
                else buf[bufLen++] = ch;
            }
            else {
                if (bufLen == 1) { // Значит в buf имя переменной/цифра и переносим в выходню строку
                    outstr.append(buf[0]);
                    bufLen = 0;
                }
                outstr.append(ch);
            }
            prev = ch;
        }
        if (bufLen > 1) {
            throw new Exception("Function without arguments");
        }
        if (bufLen > 0) {
            outstr.append(buf[0]);
        }

        return outstr.toString();
    }

//    void infix2Postfix_(String in, StringBuilder out) {
//        int i = 0;
//        int j = 0; // i - индекс во входной строке, j - в выходной
//        int row;
//        int col;
//        char action;
//        ArrayDeque<Character> S = new ArrayDeque<>();
//        boolean isP = false;
//        do {
//            col = actionsColNumber(in.charAt(i));
//            row = S.isEmpty() ? 0 : actionsRowNumber(S.peek());
//            action = actionsTable[row][col];
//            switch (action) {
//                case 1: out.append(in.charAt(i));++j; ++i; isP = true; break;
//                case 2: S.push(in.charAt(i)); ++i; if (isP) { out[j] = '.'; ++j; isP = 0; } break;
//                case 3:  out[j] = S.top(); ++j; S.pop();  break;
//                case 4: S.pop(); ++i; break;
//                case 5: throw ErrorBracketsClose(instr, i); break;
//                case 6: throw ErrorBracketsOpen(instr, i); break;
//                case 7: outstr[j] = '\0'; break;
//                case 8: throw ErrorFunctionBrackets(instr, i); break;
//                case 9: throw ErrorRValue(); break;
//            }
//        } while (action != 7);
//    }


}

