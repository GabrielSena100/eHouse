tomcat=apache-tomcat-6.0.53.tar.gz
java6=jre-6u45-linux-x64.bin
echo -e " - Instalando $java6"
echo -e " - Criando pasta /opt/java"
sudo mkdir -p /opt/java/ 
echo -e " - Movendo $java6 para /opt/java"
sudo cp $java6 /opt/java 
echo -e " - Entrando na pasta /opt/java"
cd /opt/java
echo -e " - Setando Permissoes"
sudo chmod 755 /opt/java/$java6
echo -e " - Instalando $java6" 
sudo ./$java6
echo -e " - Criando atalho jre"
sudo ln -s jre1.6.0_45 jre
echo -e " - update-alternatives em andamento"
sudo update-alternatives --install "/usr/bin/java" "java" "/opt/java/jre/bin/java" 1 
sudo update-alternatives --set java /opt/java/jre/bin/java 
sudo update-alternatives --install "/usr/bin/javaws" "javaws" "/opt/java/jre/bin/javaws" 1
sudo update-alternatives --set javaws /opt/java/jre/bin/javaws
echo -e " - fim da Instalação do Java!"
sleep 3
echo -e " - Instalando Tomcat6\n   __________________\n\n"
echo -e " - Criando pasta /opt/tomcat6"
sudo mkdir -p /opt/tomcat6
echo -e " - Copiando instalador $tomcat para /opt/tomcat6"
sudo cp ~/$tomcat /opt/tomcat6/
cd /opt/tomcat6
echo -e " - Setando permissoes do $tomcat"
sudo chmod +x $tomcat
echo -e " - Descompactando $tomcat"
sudo tar xvf $tomcat
echo -e " - Copiando ScadaBR para o Destino"
sudo cp ~/ScadaBR.war /opt/tomcat6/apache-tomcat-6.0.53/webapps/
echo -e " - Iniciando tomcat6: /opt/tomcat6/apache-tomcat-6.0.53/bin/startup.sh"
sudo /opt/tomcat6/apache-tomcat-6.0.53/bin/startup.sh
