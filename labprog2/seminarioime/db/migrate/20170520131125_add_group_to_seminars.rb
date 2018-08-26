class AddGroupToSeminars < ActiveRecord::Migration[5.1]
  def change
    add_reference :seminars, :group, foreign_key: true
  end
end
