echo "Creating /etc/apt/keyrings with proper perm..."
sudo mkdir -p -m0755 /etc/apt/keyrings

echo "Downloading Koromix GPG key..."
sudo curl -fsSL \
    https://download.koromix.dev/debian/koromix-archive-keyring.gpg \
    -o /etc/apt/keyrings/koromix-archive-keyring.gpg

echo "Adding Koromix repo..."
echo \
    "deb [signed-by=/etc/apt/keyrings/koromix-archive-keyring.gpg] \
https://download.koromix.dev/debian stable main" \
    | sudo tee /etc/apt/sources.list.d/koromix.dev-stable.list > /dev/null

echo "Updating APT and installing tytools..."
sudo apt update
sudo apt install -y tytools
