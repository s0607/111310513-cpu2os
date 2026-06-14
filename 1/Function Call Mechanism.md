函式呼叫機制（Function Call Mechanism）

P0 編譯器使用 Stack（堆疊） 管理函式呼叫。當執行 CALL 時，系統會：

    建立新的 Stack Frame（Activation Record）。
    儲存返回位址（Return Address）及相關資訊。
    配置函式的區域變數空間。
    執行函式內容。
    執行 RET（或 OPR 0）後，釋放 Stack Frame，回到原本呼叫的位置繼續執行。
流程
Main
  ↓
CALL A
  ↓
建立 Stack Frame
  ↓
執行函式 A
  ↓
RET
  ↓
返回 Main 繼續執行
函式呼叫就是利用堆疊保存執行狀態，函式結束後再恢復原本狀態，讓程式能正確回到呼叫位置繼續執行。
對話
https://chatgpt.com/share/6a2e7521-984c-83e8-b7ca-82e1368466e2