<?php

$arr = [
    "users" => [
        [
            "username" => "username",
            "email" => "email",
            "initialized" => true,
            "creationTime" => 1,
            "saveSlots" => [
                [
                    "worldId" => 1,
                    "roomId" => 1,
                    "slotName" => "Slotname lol",
                    "items" => [[
                        "id" => 1,
                        "quantity" => 1
                    ]
                    ]
                ]
            ]
        ]
    ]
];
$e = explode("\n", json_encode($arr, JSON_PRETTY_PRINT));
foreach ($e as $f) {
    $f = str_replace("\"", '\"', $f);
    echo 'printf("' . $f . '\\n"' . ");\n";
}
