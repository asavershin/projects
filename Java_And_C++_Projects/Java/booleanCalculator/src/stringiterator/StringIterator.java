package stringiterator;

import java.util.Iterator;

public class StringIterator implements Iterator<Character> {

    private String str;
    private int index;

    public StringIterator(String str) {
        this.str = str;
        this.index = 0;
    }

    public Character current(){
        return str.charAt(index);
    }

    @Override
    public boolean hasNext() {
        return index < str.length();
    }

    @Override
    public Character next() {
        if (!hasNext()) {
            throw new IllegalStateException("End of string reached.");
        }
        return str.charAt(index++);
    }

}
