fun logn_power(x : int, n : int)=
  case n of
       0 => 1
     | 1 => x
     | _ => let
              val w = if (n mod 2) > 0 then x else 1
            in
              logn_power(x, n div 2) * logn_power(x, n div 2) * w
            end
