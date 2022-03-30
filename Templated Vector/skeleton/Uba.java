import java.util.Arrays;

/*
 * Lab02.
 *
 *
*  Adding extra helper functions is allowed and would be a good idea.
 * Extra class variables can be added but are not required to solve this lab.
 *
 * It's always a good idea to split your logic into multiple functions since each
 * function should ideally do one thing and do it well.
 *
 * Good luck! Have fun! (If you're not having fun ask CPs for help :-)
*/


public class Uba<AnyType>  implements UbaInterface<AnyType>
{
    private static final int DEFAULT_CAPACITY = 5;

    private AnyType[] items;
    private int size; // the current number of elements in the array
    private int max_size;

  /**
	*  Constructs an empty array of default capacity
	*/
	@SuppressWarnings("unchecked")
	public Uba()
	{
        items = (AnyType[])new Object[5];
        size = 0;
        max_size=5;
	}
	
	public void resize() {
		max_size*=2;
		AnyType[] copy_array=(AnyType[]) new Object[max_size];
		for(int i=0;i<items.length;i++) {
			copy_array[i]=items[i];
		}
		items =copy_array;
	}


  /**
	*  Adds an item to this collection, at the end.
	*/
	public void add(AnyType x)
	{
		if(size==max_size) {
			resize();
		}
        items[size]=x;
        size++;
	}

  /**
	*   Removes the last item from the list and returns it
	*/
	public AnyType remove()
	{
        // Todo: Implement
        if(size==0) {
        	return null;
        }
        size--;
        return items[size];
        
     
	}
	


  /**
	*  Returns a string representation
	*/
	@Override
	public String toString( )
	{
        // Todo: Implement
		AnyType[] string_array = (AnyType[]) new Object[size];
		for(int i=0;i<size;i++) {
			string_array[i]=items[i];
		}
		return Arrays.toString(string_array);
	}

	public static void main(String[] args)
	{
		Uba<Integer> tmp = new Uba<Integer> ();
		System.out.println(tmp);

		for(int i = 0; i < 50; i++) tmp.add(i);
		System.out.println(tmp);

		System.out.println(tmp.remove());
		System.out.println(tmp);

		Uba< String > tmp1 = new Uba<String> ();
		for(int i = 0; i < 6; i++) tmp1.add("uba" + i);
		System.out.println(tmp1);

		System.out.println(tmp1.remove());
		System.out.println(tmp1);

	}

}