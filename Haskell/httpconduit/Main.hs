import Network.HTTP.Conduit
import qualified Data.ByteString.Lazy as Lazy

main :: IO ()
main = simpleHttp "http://www.winsoft.sk" >>= Lazy.putStr
