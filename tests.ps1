
$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
Push-Location $projectRoot

try {
    Write-Host "`nCompiling Regex Evaluator..." -ForegroundColor Cyan

    $sourceFiles = Get-ChildItem -Path "src" -Filter "*.cpp" |
        ForEach-Object { $_.FullName }

    & g++ -Iinclude $sourceFiles -o src/a.exe

    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed!" -ForegroundColor Red
        exit 1
    }

    Write-Host "Compilation successful!`n" -ForegroundColor Green

    $tests = @(
        @{ Name = "Literal match"; Regex = "a"; Input = "a"; Expected = "ACCEPT" }
        @{ Name = "Literal mismatch"; Regex = "a"; Input = "b"; Expected = "REJECT" }
        @{ Name = "Concatenation"; Regex = "abc"; Input = "abc"; Expected = "ACCEPT" }
        @{ Name = "Union match"; Regex = "a|b"; Input = "b"; Expected = "ACCEPT" }
        @{ Name = "Union mismatch"; Regex = "a|b"; Input = "c"; Expected = "REJECT" }
        @{ Name = "Star match"; Regex = "a*"; Input = "aaa"; Expected = "ACCEPT" }
        @{ Name = "Star with empty input"; Regex = "a*"; Input = ""; Expected = "ACCEPT" }
        @{ Name = "Star mismatch"; Regex = "a*"; Input = "b"; Expected = "REJECT" }
        @{ Name = "Parentheses"; Regex = "(a|b)"; Input = "b"; Expected = "ACCEPT" }
        @{ Name = "Nested expression match"; Regex = "((a|b)*)"; Input = "abba"; Expected = "ACCEPT" }
        @{ Name = "Nested expression mismatch"; Regex = "((a|b)*)"; Input = "abc"; Expected = "REJECT" }
        @{ Name = "Complex expression match"; Regex = "(a|b)*abb"; Input = "abababb"; Expected = "ACCEPT" }
        @{ Name = "Complex expression mismatch"; Regex = "(a|b)*abb"; Input = "ab"; Expected = "REJECT" }
        @{ Name = "Empty regex and input"; Regex = ""; Input = ""; Expected = "ACCEPT" }
        @{ Name = "Empty regex with text"; Regex = ""; Input = "abc"; Expected = "REJECT" }
        @{ Name = "Trailing union"; Regex = "a|"; Input = "a"; Expected = "REJECT" }
        @{ Name = "Standalone star"; Regex = "*"; Input = "a"; Expected = "REJECT" }
        @{ Name = "Repeated star"; Regex = "a**"; Input = "aaa"; Expected = "REJECT" }
        @{ Name = "Missing closing parenthesis"; Regex = "(a|b"; Input = "a"; Expected = "REJECT" }
        @{ Name = "Extra closing parenthesis"; Regex = "a)"; Input = "a"; Expected = "REJECT" }
        @{ Name = "Empty group"; Regex = "()"; Input = ""; Expected = "REJECT" }
    )

    $passed = 0
    $failed = 0

    foreach ($test in $tests) {
        $testInput = [string]$test.Regex + "`n" +
                     [string]$test.Input + "`n"

        $output = $testInput | & ".\src\a.exe" 2>&1 | Out-String

        if ($output -match "Result: $([regex]::Escape($test.Expected))") {
            Write-Host "[PASS] $($test.Name)" -ForegroundColor Green
            $passed++
        }
        else {
            Write-Host "[FAIL] $($test.Name)" -ForegroundColor Red
            Write-Host "       Expected: $($test.Expected)"
            Write-Host "       Actual output: $($output.Trim())"
            $failed++
        }
    }

    Write-Host "`n========== TEST SUMMARY =========="
    Write-Host "Total:  $($passed + $failed)"
    Write-Host "Passed: $passed" -ForegroundColor Green
    Write-Host "Failed: $failed" -ForegroundColor $(if ($failed -gt 0) { "Red" } else { "Green" })

    if ($failed -gt 0) {
        exit 1
    }
}
finally {
    Pop-Location
}