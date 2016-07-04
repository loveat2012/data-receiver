<?php
$fp = stream_socket_client("tcp://0.0.0.0:8000", $errno, $errstr, 30);
if (!$fp) {
    echo "$errstr ($errno)<br />\n";
} else {
    fwrite($fp, "aaa");
    while (!feof($fp)) {
        $ret = fgets($fp, 4);
        var_dump($ret);
        if ($ret == '000') {
            break;
        } else {
            // Log ...
        }
    }
    fclose($fp);
}
