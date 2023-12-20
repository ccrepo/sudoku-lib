
public class sudoku_libclient_moves {
  public static void main(String[] args) {

    System.out.println("start"); 

    try {
      System.loadLibrary("sudoku");
    } catch (Exception e) {
      System.err.println("exception: " + e.toString());      
    }

    sudoku_jlib sudoku_jlib_i = new sudoku_jlib();

    int buffer_size = sudoku_jlib_i.getL_CONST_RESULT_BUFFER_SIZE();

    System.out.println("sudoku jlib buffer size " + buffer_size);

    String in_position = new String("7 0 9 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ");

    SWIGTYPE_p_unsigned_char out_moves = sudoku_jlib_i.new_uint8Array(buffer_size);

    int[] runtime = new int[] { -1 };

    try {

      sudoku_jlib_i.get_sudoku_possible_moves_STUB(in_position, out_moves, runtime);

      StringBuilder buffer = new StringBuilder();

      for (int i = 0; i<buffer_size; ++i) {

        short item = sudoku_jlib_i.uint8Array_getitem(out_moves, i);

        if (item == 0) {
          break;
        }

        buffer.append((char) item);
      }

      System.out.println("moves: '" + buffer.toString() + "'");

      System.out.println("runtime: " + (runtime[0] == -1 ? "n/a" : Integer.toString(runtime[0])) + "ms");

    } catch (Exception e1) {	
      System.out.println("exception calling get moves stub " + e1); 
    } 

    try {
      sudoku_jlib_i.delete_uint8Array(out_moves);
    } catch (Exception e2) {
      System.out.println("exception deleting memory: " + e2); 
    }

    System.out.println("end");
  }
}
