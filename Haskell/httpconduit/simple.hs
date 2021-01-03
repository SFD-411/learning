import Network.HTTP.Conduit
import qualified Data.ByteString.Lazy as Lazy

main = simpleHTTP "http://www.winsoft.sk" >>= Lazy.putStr
