function countAlphabets(input) {
    const counts = {};

    // 알파벳 카운트 초기화
    for (let char of input) {
        if (/[a-zA-Z]/.test(char)) {
            char = char.toLowerCase();
            counts[char] = 0;
        }
    }

    // 알파벳 카운트
    for (let char of input) {
        if (/[a-zA-Z]/.test(char)) {
            char = char.toLowerCase();
            counts[char]++;
        }
    }

    // 결과 출력
    for (let alphabet in counts) {
        console.log(`${alphabet}: ${counts[alphabet]}`);
    }
}

const readline = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});

readline.question("알파벳을 입력하세요: ", (input) => {
    countAlphabets(input);
    readline.close();
});
