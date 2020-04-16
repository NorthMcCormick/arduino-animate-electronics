if [[ ! -d "/Volumes/Home Directory/main" ]]
then
    open afp://10.0.0.53
fi

rm -r "/Volumes/Home Directory/main/"

cp -r ./src "/Volumes/Home Directory/main"

ssh  -o PreferredAuthentications=publickey -o PubkeyAuthentication=yes pi@octopi.local "sh ~/build.sh"