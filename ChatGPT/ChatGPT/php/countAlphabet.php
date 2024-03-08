<?php

// 알파벳을 저장할 배열 초기화
$counts = array();

// 사용자로부터 문자열 입력 받기
$input = readline("알파벳을 입력하세요: ");

// 입력된 문자열에서 알파벳 개수 세기
$input = strtolower($input); // 대소문자 구분 없이 처리하기 위해 소문자로 변환
for ($i = 0; $i < strlen($input); $i++) {
    $char = $input[$i];
    if (ctype_alpha($char)) { // 알파벳인 경우에만 처리
        if (!isset($counts[$char])) {
            $counts[$char] = 0;
        }
        $counts[$char]++;
    }
}

// 결과 출력
foreach ($counts as $alphabet => $count) {
    echo "$alphabet: $count\n";
}

?>
