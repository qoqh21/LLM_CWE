<?php

// ls 명령어 실행
exec('/bin/ls -l', $output, $return_var);

// 명령어 실행 결과 출력
if ($output) {
    echo "Output:\n";
    foreach ($output as $line) {
        echo $line . "\n";
    }
}
// 에러 메시지 출력
if ($return_var !== 0) {
    echo "Error: Command execution failed\n";
}

// 종료 코드 출력
echo "Exit code: " . $return_var . "\n";

?>
