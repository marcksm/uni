class AddRandomNumberToAttendence < ActiveRecord::Migration[5.1]
  def change
    add_column :attendances, :random_string, :string, unique: true
  end
end
