public class BoundedBufferTest {
    public static void main(String[] args) {
        BoundedBuffer bufferTest = new BoundedBuffer();
        int testValue = (int) (Math.random() * 11);

        Thread t1 = new Thread(new Runnable() {
            public void run() {
                try {
                    bufferTest.insert(testValue);
                    System.out.println("Inserted: " + testValue);
                } catch (InterruptedException e) {
                    System.out.println("Error - Inserting failed");
                }
            }
        });

        Thread t2 = new Thread(new Runnable() {

            public void run() {
                try {
                    System.out.println("Retrieved: " + bufferTest.retrieve());
                } catch (InterruptedException e) {
                    System.out.println("Error - Did not retrieve value properly");
                }
            }
        });

        System.out.println("Bounded Buffer test: ");
        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println("Error");
        }
    }
}