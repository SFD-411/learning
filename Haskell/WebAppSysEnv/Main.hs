import Network.URI
import Happstack.Server.Env
import System.Environment

main :: IO()
main = do
    environment <- getEnvironment
    simpleHTTP nullConf $ ok $ show environment
