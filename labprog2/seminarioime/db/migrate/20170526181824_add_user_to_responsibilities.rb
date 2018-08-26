class AddUserToResponsibilities < ActiveRecord::Migration[5.1]
  def change
    add_reference :responsibilities, :user, foreign_key: true
  end
end
