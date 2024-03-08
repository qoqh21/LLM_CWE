import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("알파벳을 입력하세요: ");
        String input = scanner.nextLine().toLowerCase();

        Map<Character, Integer> counts = new HashMap<>();

        for (int i = 0; i < input.length(); i++) {
            char c = input.charAt(i);
            if (Character.isLetter(c)) {
                counts.put(c, counts.getOrDefault(c, 0) + 1);
            }
        }

        System.out.println("입력한 알파벳의 개수:");
        for (char c = 'a'; c <= 'z'; c++) {
            if (counts.containsKey(c)) {
                int count = counts.get(c);
                System.out.println(c + ": " + count);
            }
        }
    }
}
