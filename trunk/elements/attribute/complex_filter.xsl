<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="attr_name" label="Attribute name" />
            <attribute name="creation" label="Type of creation"/>
            <attribute name="ctgr_count" label="Count of categories" numeric_sort="true"/>
            <attribute name="ctgr_list" label="List of categories"/>
            <attribute name="missing_values" label="Missing values"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="attr_name" label="Jméno atributu" />
            <attribute name="creation" label="Způsob vytvoření"/>
            <attribute name="ctgr_count" label="Počet kategorií" numeric_sort="true"/>
            <attribute name="ctgr_list" label="Seznam kategorií"/>
            <attribute name="missing_values" label="Chybějící hodnoty"/>
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->
      </attributes>

      <values>
        <xsl:apply-templates select="attribute" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>


  
  
  


  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<xsl:text disable-output-escaping="yes">ctgr_list="</xsl:text>
		<xsl:apply-templates select="ctgr" mode="values"/>
		<xsl:text disable-output-escaping="yes">" </xsl:text>
		
		<xsl:text disable-output-escaping="yes">missing_values="</xsl:text>
		<xsl:apply-templates select="missing_value" mode="values"/>
		<xsl:text disable-output-escaping="yes">"</xsl:text>

		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>


<!-- ================= TEMPLATE ============================== -->


	<!-- naplni hodnotu pro categories -->
	<xsl:template match="ctgr" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@name"/>
		<!--<xsl:text disable-output-escaping="no"> (</xsl:text>
		<xsl:value-of select="@freq"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>-->
	</xsl:template>



	<!-- naplni hodnotu pro missing_values -->
	<xsl:template match="missing_value" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@name"/>
	</xsl:template>



<!-- ================= TEMPLATE ============================== -->


	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
