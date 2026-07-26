/*
 講師陣はどのようなコメントを残すだろうか？
 他の人のコードを読んで考えたこと
  - https://github.com/Yoshiki-Iwasa/Arai60/pull/63/files
    1. Rustのlet Some, unreachable!マクロわかりやすくていい
    2. pivotやsuccessorの名前がわかりやすい
    3. pivotやsuccessorを見つける際がワンライナーで書けている。
       C++だとどう書けるだろうか。
    4. rpositionに当たるような右から見ていく関数はあっただろうか
    https://doc.rust-lang.org/std/iter/trait.Iterator.html#method.rposition
  - https://github.com/fhiyo/leetcode/pull/56/files
    1. 二重ループのコードは計算量的に無駄があるし、何をしているのか
       自分としては少しわかりにくいと感じたが、なるほど確かに短くは書けるのか。
    2. 関数や変数名についてみんな迷っていたが、pivot, successorなどのようにその
       変数がそもそも何なのか、概念を見つけられれば名前がつけやしのかもしれない。
       そうではなく、手続きややっていることを説明しようとすると、長くてわかりに
       くくなってしまうのだろう。
       （そもそもprogram自体が指示の羅列なのだから読めばわかるもの）

 改善する時にかんがえたこと
   1. algorithm関連 : cppreferenceを見てみて、使えそうな関数を探してみる
    https://en.cppreference.com/w/cpp/algorithm/find
    https://en.cppreference.com/w/cpp/algorithm/find_end
    https://en.cppreference.com/w/cpp/algorithm/adjacent_find
    https://en.cppreference.com/w/cpp/algorithm/lower_bound
    https://en.cppreference.com/w/cpp/algorithm/upper_bound
    https://en.cppreference.com/w/cpp/algorithm/iter_swap
   2. Iterator関連 : cppreferenceを見てみて、使えそうな関数を探してみる
    https://en.cppreference.com/w/cpp/iterator/rbegin
    https://en.cppreference.com/w/cpp/iterator/rend
    https://en.cppreference.com/w/cpp/iterator/prev
    https://en.cppreference.com/w/cpp/iterator/next
    https://en.cppreference.com/w/cpp/iterator/advance
    https://en.cppreference.com/w/cpp/iterator/distance
   3. rbeginとrendを使えば後ろから舐めていける
   4. adjacent_findとupper_boundが今回の例にはピッタリ
   5. reverse(begin, pivot)としておけば最初に降順ペアが見つからなかった場合にも
      正しく動作するのでearly returnしなくても一箇所にまとめられる。
 */
class Solution {
public:
  void nextPermutation(std::vector<int> &nums) {
    // Find the first DSC pair from the tail : [4,(5,7),6,3,2,1]
    auto pivot =
        std::adjacent_find(nums.rbegin(), nums.rend(), std::greater<int>());
    if (pivot != nums.rend()) {
      ++pivot; // to point to the second element of the pair :
               // [4,(*5,7),6,3,2,1]
      // to find the successor of pivot : [4,(*5,7),**6,3,2,1]
      auto successor = std::upper_bound(nums.rbegin(), pivot, *pivot);
      std::iter_swap(pivot, successor);
    }
    std::reverse(nums.rbegin(), pivot);
  }
};
