package workspace.formulanodes;

public class ParamValue implements Comparable<ParamValue> {
    int ch;
    protected boolean val;
    public ParamValue(int ch, boolean val){
        this.ch = ch;
        this.val = val;
    }
    public int getCh(){
        return ch;
    }
    public void setVal(boolean newVal){
        this.val = newVal;
    }
    public boolean lessThan(int ch) {
        return this.ch < ch;
    }

    public boolean equals(int ch) {
        return this.ch == ch;
    }

    @Override
    public int compareTo(ParamValue o) {
        return Integer.compare(ch, o.ch);
    }
}
