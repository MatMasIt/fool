<?php

$arr = [
    "uid" => 1,
    "worlds" => [
        [
            "ID" => 1,
            "name" => "Testlandia",
            "desc" => "Uh, a test world",
            "rooms" => [
                [
                    "ID" => 1,
                    "name" => "Liceo cocito",
                    "desc" => "It has been teleported into mt. Vesuvius",
                    "musicFile" => "funiculi",
                    "paths" => [
                        ["dir" => "N", "toRoomId" => 2]
                    ],
                    "items" => [["ID" => 3, "name" => "Giulio Andreotti", "desc" => "Change the world.... My final message\nGoodbye!", "healtheffect" => -10]]
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
