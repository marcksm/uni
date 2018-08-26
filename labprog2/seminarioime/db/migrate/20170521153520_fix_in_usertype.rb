class FixInUsertype < ActiveRecord::Migration[5.1]
  def change
      change_column :users, :usertype, :boolean, :default => false
  end
end
