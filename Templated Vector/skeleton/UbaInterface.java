public interface UbaInterface<AnyType>
{
    // Inserts an item at the end of the list
    public void add(AnyType obj);

    // Removes the last item from the list and returns it
    public AnyType remove();

    // Returns a string representation of the list
    public String toString();
    
    public void resize();
}
