o "Please release your fingers from the keyboard."
# 
# sleep 3

git status

echo """
Do the above modifications look right to you? Is there a change you didn't mean to change? If so, press Ctrl+C to stop this program, and then run 'git revert <file_to_revert>. Otherwise, press enter to continue: '
"""
read nonsense_var

git add -A
git checkout -- .settings/language.settings.xml
git reset HEAD .settings/language.settings.xml

echo "What is your github username?: "
read username
echo "What is your github email?: "
read email

git config --global user.name "$username"
git config --global user.email  "$email"

echo """
Please take a few moments to create a commit message in your favorite text editor. It should follow the following format:

Short heading describes major changes #1, #2, #3.

Describe major change #1 in detail in a paragraph. What problems did you run into, is your code tested for this change?

Describe major change #2 in detail in a paragraph. What problems did you run into, is your code tested for this change?

Describe major change #3 in detail in a paragraph. What problems did you run into, is your code tested for this change?

=======================================================================================================================
PLEASE PASTE YOUR COMMIT MESSAGE HERE, WHEN FINISHED PRESS CTRL+D UNTIL SOMETHING HAPPENS (DO NOT HOLD CTRL+D!!!):
"""
commit=$(cat)

git commit -m "$commit"
git push


