class AddUserToInterest < ActiveRecord::Migration[5.1]
  def change
    add_reference :interests, :user, foreign_key: true
  end
end
